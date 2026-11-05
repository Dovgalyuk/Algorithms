function plot_stress(csv_file, output_dir)
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
    data = textscan(file, '%f %s %f %f %f', 'Delimiter', ',', 'HeaderLines', 1);
    fclose(file);
    names = {'insert', 'find', 'erase'};
    titles = {'Insert + size check', 'Find + value check', 'Erase + absence and size checks'};
    fig = figure('visible', 'off', 'position', [100 100 1450 500]);
    graphics_toolkit(fig, 'gnuplot');
    for i = 1:3
        subplot(1, 3, i);
        hold on;
        selected = strcmp(data{2}, names{i});
        n = data{1}(selected);
        seconds = data{3}(selected);
        low = seconds - data{4}(selected);
        high = data{5}(selected) - seconds;
        [n, order] = sort(n);
        seconds = seconds(order);
        measured = errorbar(n, seconds, low(order), high(order), '-o');
        set(measured, 'color', [0.15 0.40 0.75], 'linewidth', 1.5);
        % Reference curves are anchored at the first measured point.
        linear = seconds(1) * n / n(1);
        quadratic = seconds(1) * (n / n(1)).^2;
        plot(n, linear, '--', 'color', [0.15 0.60 0.35]);
        plot(n, quadratic, ':', 'color', [0.85 0.35 0.12]);
        xlim([min(n)/1.3 max(n)*1.3]);
        ylim([min(data{4}(selected))/1.5 max(quadratic)*2]);
        set(gca, 'xscale', 'log', 'yscale', 'log', 'fontsize', 10);
        title(titles{i});
        xlabel('Number of unique pairs');
        ylabel('Phase time, seconds (including file reading)');
        grid on;
        text(0.04, 0.95, 'BWA median; bars: min/max', 'units', 'normalized', 'color', [0.15 0.40 0.75]);
        text(0.04, 0.89, 'Reference N', 'units', 'normalized', 'color', [0.15 0.60 0.35]);
        text(0.04, 0.83, 'Reference N^2', 'units', 'normalized', 'color', [0.85 0.35 0.12], 'interpreter', 'none');
    end
    print(fig, fullfile(output_dir, 'stress_scaling.png'), '-dpng', '-r150');
    close(fig);
end
