function plot_results(csv_file, output_dir)
    if nargin < 2
        output_dir = fileparts(csv_file);
        if isempty(output_dir)
            output_dir = '.';
        end
    end
    if ~exist(output_dir, 'dir')
        mkdir(output_dir);
    end

    file = fopen(csv_file, 'r');
    if file == -1
        error('Cannot open CSV file');
    end
    data = textscan(file, '%f %s %f %f %f', ...
                    'Delimiter', ',', 'HeaderLines', 1);
    fclose(file);

    names = {'BWA', 'map', 'unordered_map'};
    labels = {'BWA', 'std::map', 'std::unordered_map'};
    colors = [0.15 0.40 0.75; 0.85 0.35 0.12; 0.15 0.60 0.35];

    fig = figure('visible', 'off', 'position', [100 100 1200 520]);
    graphics_toolkit(fig, 'gnuplot');
    for panel = 1:2
        subplot(1, 2, panel);
        hold on;
        for i = 1:3
            selected = strcmp(data{2}, names{i});
            n = data{1}(selected);
            seconds = data{3}(selected);
            low = seconds - data{4}(selected);
            high = data{5}(selected) - seconds;
            [n, order] = sort(n);
            line = errorbar(n, seconds(order), low(order), high(order), '-o');
            set(line, 'color', colors(i, :), 'linewidth', 1.5, 'markersize', 5);
        end
        if panel == 2
            xlim([min(data{1}) / 1.3, max(data{1}) * 1.3]);
            ylim([min(data{4}) / 1.5, max(data{5}) * 1.5]);
            set(gca, 'xscale', 'log', 'yscale', 'log');
            title('Logarithmic axes');
        else
            title('Linear axes');
            xlim([0 max(data{1}) * 1.05]);
            ylim([0 max(data{5}) * 1.15]);
        end
        xlabel('Number of unique pairs');
        ylabel('Insertion time, seconds');
        grid on;
        for i = 1:3
            text(0.04, 0.96 - (i-1)*0.06, labels{i}, 'units', 'normalized', ...
                 'color', colors(i,:), 'fontsize', 12, 'interpreter', 'none');
        end
        set(gca, 'fontsize', 11);
    end
    print(fig, fullfile(output_dir, 'loading_time.png'), '-dpng', '-r150');
    close(fig);

    fig = figure('visible', 'off', 'position', [100 100 850 520]);
    graphics_toolkit(fig, 'gnuplot');
    hold on;
    for i = 1:3
        selected = strcmp(data{2}, names{i});
        n = data{1}(selected);
        seconds = data{3}(selected);
        [n, order] = sort(n);
        semilogx(n, 1e6 * seconds(order) ./ n, '-o', ...
                 'color', colors(i, :), 'linewidth', 1.5);
    end
    set(gca, 'xscale', 'log', 'fontsize', 11);
    xlabel('Number of unique pairs');
    ylabel('Insertion time per pair, microseconds');
    title('Median insertion time / number of pairs');
    for i = 1:3
        text(0.04, 0.96 - (i-1)*0.06, labels{i}, 'units', 'normalized', ...
             'color', colors(i,:), 'fontsize', 12, 'interpreter', 'none');
    end
    grid on;
    ylim([0 Inf]);
    print(fig, fullfile(output_dir, 'time_per_pair.png'), '-dpng', '-r150');
    close(fig);
    fprintf('Graphs saved to %s\n', output_dir);
end
